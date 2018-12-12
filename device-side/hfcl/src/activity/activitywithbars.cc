/*
** HFCL - HybridOS Foundation Class Library
**
** Copyright (C) 2018 Beijing FMSoft Technologies Co., Ltd.
**
** This file is part of HFCL.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "activity/activitywithbars.h"

namespace hfcl {

ActivityWithBars::ActivityWithBars ()
    : TimerEventListener (1)
    , m_isFullScreen(false)
#ifdef __SUPPORT_MANUAL_KEYPAD_LOCK_IN_ALLSCREEN__
    , m_isShowLockPopup(false)
#endif
    , m_menuBarShown(true)
    , m_menuId(0)
    , m_keyDownTarget(NULL)
    , m_keyDownCode(-1)
    , m_tipShown(false)
{
    m_timerId = 0;
    m_menuBar = MenuBar::getInstance();
    m_indicator = Indicator::getInstance();
    m_usedLang = GetResourceLanguage();
}

ActivityWithBars::ActivityWithBars (bool fullscreen)
    : TimerEventListener(1)
    , m_isFullScreen(fullscreen)
    , m_menuBarShown(true)
    , m_menuId(0)
    , m_keyDownTarget(NULL)
    , m_keyDownCode(-1)
    , m_tipShown(false)
{
    m_timerId = 0;
    m_menuBar = MenuBar::getInstance();
    m_indicator = Indicator::getInstance();
    m_usedLang = GetResourceLanguage();
}

ActivityWithBars::~ActivityWithBars()
{
    closeTimer();
    m_indicator->detachFromeViewTree(this);
    m_menuBar->detachFromeViewTree(this);
}

void ActivityWithBars::onCreate(ContextStream* contextStream, Intent* intent)
{
    FullScreenActivity::onCreate(contextStream, intent);
}

void ActivityWithBars::showMenuBar(bool show)
{
    m_menuBarShown = show;
    if (ActivityManager::getInstance()->getCurrentActivity() == this) {
        refreshMenubar();
    }
}

void ActivityWithBars::showIndicator(bool show)
{
    m_isFullScreen = !show;
    if (ActivityManager::getInstance()->getCurrentActivity() == this) {
        refreshIndicator();
    }
}

unsigned int ActivityWithBars::onClientCommand(int sender,
        unsigned int cmd_id, HTData param1, HTData param2)
{
    switch (cmd_id) {
    case LOCKFRAME_EVENT_UPDATE_MISSED_CALL_NOTICE:
    case LOCKFRAME_EVENT_UPDATE_SMS_NOTICE:
    case LOCKFRAME_EVENT_CLEAR_LOCKFRAME:
        passCommandToClient(APP_CLIENT_LOCKFRAME, cmd_id, param1, param2);
        break;
    }

    return 0;
}

unsigned int ActivityWithBars::setMode(ControllerModeList* modelist)
{
    bool bsetphonebar = false;

    if (modelist == NULL
        || ActivityManager::getInstance()->getCurrentActivity() != this) {
        return 0;
    }

    /* VincentWei > OPT: do not clear old modes
    SetMenuBarLeftText(0);
    SetMenuBarRightText(0);
    SetMenuBarMiddleText(0);
    SetMenuBarLeftImage(NULL);
    SetMenuBarRightImage(NULL);
    SetMenuBarMiddleImage(NULL);
    */

    for(int i = 0; i < modelist->mode_count; i++) {
        unsigned int value = modelist->modes[i].value;
        unsigned int cmd = modelist->modes[i].cmd;
        switch(modelist->modes[i].id) {
        case APP_MENUBAR_LEFTTEXT:
            SetMenuBarLeftText(value);
            m_menubarCmds[0] = cmd;
            break;
        case APP_MENUBAR_MIDDLETEXT:
            SetMenuBarMiddleText(value);
            m_menubarCmds[1] = cmd;
            break;
        case APP_MENUBAR_RIGHTTEXT:
            SetMenuBarRightText(value);
            m_menubarCmds[2] = cmd;
            break;
        case APP_OPTION_MENU:
            m_menuId = (ResID) value;
            break;
        case APP_MENUBAR_LEFTIMAGE:
            SetMenuBarLeftImage(GetImageRes(value));
            m_menubarCmds[0] = cmd;
            break;
        case APP_MENUBAR_RIGHTIMAGE:
            SetMenuBarRightImage(GetImageRes(value));
            m_menubarCmds[2] = cmd;
            break;
        case APP_MENUBAR_MIDDLEIMAGE:
            SetMenuBarMiddleImage(GetImageRes(value));
            m_menubarCmds[1] = cmd;
            break;
        case APP_STATUSBAR_SCRTYPE:
            if (m_indicator)
                m_indicator->setIndicatorType(value, cmd);
            bsetphonebar = true;
            break;
        }
    }

    if(!bsetphonebar && m_indicator)
        m_indicator->getPhoneBar()->setBkColor(0xFF1A1A1A);
    return 0;
}

bool ActivityWithBars::onKey(int keyCode, KeyEvent* event)
{
    LcdService *lcd_service = LcdService::getInstance();
    lcd_service->reset (true);

    if (ActivityManager::getInstance()->getCurrentActivity() != this) {
        return DISPATCH_STOP_MSG;
    }

    ActivityClient* top_app = (ActivityClient*)getTop(0);
    bool ret = true;

    if(top_app && keyCode == KeyEvent::KEYCODE_SR) {
        if (event->eventType() == Event::KEY_DOWN && event->keyStatus() == 0) {
            // VincentWei: only call openTimer for first KEYDOWN event
            openTimer();
        }
        else if (event->eventType() == Event::KEY_UP) {
            closeTimer();
        }
    }

    if(top_app != NULL) {
        if ((event->eventType() == Event::KEY_DOWN)
                || (event->eventType() == Event::KEY_LONGPRESSED)
                || (event->eventType() == Event::KEY_ALWAYSPRESS)) {
            m_keyDownTarget = top_app;
            m_keyDownCode = keyCode;
        }
        else if (event->eventType() == Event::KEY_UP){
            if (m_keyDownTarget != top_app || keyCode != m_keyDownCode) {
                m_keyDownTarget = NULL;
                m_keyDownCode = -1;
                return DISPATCH_STOP_MSG;
            }
            m_keyDownTarget = NULL;
        }

        if (top_app->onKey(keyCode, event) == DISPATCH_STOP_MSG) {
            return DISPATCH_STOP_MSG;
        }
    }

    if (event->eventType() == Event::KEY_DOWN
            && keyCode == KeyEvent::KEYCODE_STOP) {
        exitHome();
        return DISPATCH_STOP_MSG;
    }

    if (m_menuBar && !isImeOpen()
            && (keyCode == KeyEvent::KEYCODE_SL
                || keyCode == KeyEvent::KEYCODE_SR
                || keyCode == KeyEvent::KEYCODE_ENTER)) {

        // VincentWei: Only dispatch first KEYDOWN event (ignore repeat KEYDOWN events).
        if (event->eventType() == Event::KEY_DOWN && event->keyStatus() == 0) {
            m_menuBar->getMenuBar()->dispatchEvent (event);
        }
        else if (event->eventType() == Event::KEY_UP) {
            m_menuBar->getMenuBar()->dispatchEvent (event);

            int cmd = 0;
            switch (keyCode) {
            case KeyEvent::KEYCODE_SL:
                cmd = m_menubarCmds[0];
                break;
            case KeyEvent::KEYCODE_ENTER:
                cmd = m_menubarCmds[1];
                break;
            case KeyEvent::KEYCODE_SR:
                cmd = m_menubarCmds[2];
                break;
            }

            if (cmd != 0) {
                return doCommand(cmd);
            }
        }
    }

    ret = Activity::onKey(keyCode, event);
#ifdef __SUPPORT_MANUAL_KEYPAD_LOCK_IN_ALLSCREEN__
    if (ret == DISPATCH_CONTINUE_MSG
            && event->eventType() == Event::KEY_LONGPRESSED
            && keyCode == KeyEvent::KEYCODE_STAR) {
        enterLockFrame(true, true);
        return DISPATCH_STOP_MSG;
    }
#endif
    return ret;
}

bool ActivityWithBars::handleEvent(Event* event)
{
    if (event->eventType() == Event::CUSTOM_NOTIFY) {
        //menu notify event
        if (((CustomEvent *)event)->customWparam() == View::NOTIFY_ON_CLICK) {
            MenuBarView *m = m_menuBar->getMenuBar();
            ViewClickEventStruct *s
                = (ViewClickEventStruct*)(((CustomEvent*)event)->customLparam());

            if (s->view == m) {
                int w, h;
                m->getSize(&w, &h);
                if (s->x <= w / 3 && m_menubarCmds[0] != 0) {
                    doCommand(m_menubarCmds[0]);
                }
                else if (s->x >= w * 2 / 3 && m_menubarCmds[2] != 0) {
                    doCommand(m_menubarCmds[2]);
                }
                else if (m_menubarCmds[1] != 0) {
                    doCommand(m_menubarCmds[1]);
                }
            }

            return DISPATCH_STOP_MSG;
        }

        ActivityClient *client = getTopActivityClient();
        if (client)
            client->onMenuCommand((CustomEvent*)event);

        return DISPATCH_STOP_MSG;
    }
    else if (event->eventType() == Event::TIMER
            && m_timerId == ((TimerEvent*)event)->timerID()) {

        if (m_keyUp) {
            closeTimer();
        }
        else {
            KeyEvent event(Event::KEY_CHAR, 127, 0);
            Activity::onKey(127, &event);
        }

        return DISPATCH_STOP_MSG;
    }

    return DISPATCH_CONTINUE_MSG;
}

void ActivityWithBars::openTimer()
{
    if(m_timerId == 0) {
        m_timerId = registerTimer(50, "ActivityWithBars");
    }
    m_keyUp = false;
}

void ActivityWithBars::closeTimer()
{
    m_keyUp = true;
    if (m_timerId != 0)
        removeTimer(m_timerId);
    m_timerId = 0;
}

void ActivityWithBars::showMenu()
{
    if(!m_menuId)
        return ;

    // if press key too fast, the menu will be create,
    // but app will get active sometimes so that create
    // menu one more.so check the menu at first.if exist, show it only.
    if (menu()) {
        menu()->showMenu(this);
        return ;
    }

    Menu* menu = CreateMenuFromRes(m_menuId, NULL, this);
    if(menu) {
        //TODO here we cann add the animation for menu
        bindMenu(menu);
        menu->freeze(true);
        onMenuShow(menu);
        menu->freeze(false);
        menu->autoFit();
        menu->showMenu(this);
    }
}

/**
 * @brief Set Activity To FullScreen
 *
 * @details
 *   < Normal >               < FullScreen & show Menubar>   < FullScreen & hide Menubar >
 *  ______________________        ______________________         ______________________
 * |______Phonebar________|      |                      |       |                      |
 * |                      |      |                      |       |                      |
 * |                      |      |                      |       |                      |
 * |                      |      |                      |       |                      |
 * |    ClientContent     |      |    ClientContent     |       |    ClientContent     |
 * |                      |      |                      |       |                      |
 * |                      |      |                      |       |                      |
 * |                      |      |                      |       |                      |
 * |______________________|      |______________________|       |                      |
 * |_______Menubar________|      |_______Menubar________|       |______________________|
 *
 *
 */

void ActivityWithBars::setFullScreen(bool bfullScreen)
{
    ActivityClient* clt = getTopActivityClient();

    if(NULL != clt){
        clt->onFullScreen(bfullScreen);
        View *cltView = clt->baseView();
        if (NULL != cltView)
        {
            if (bfullScreen || clt->getId() == APP_CLIENT_LOCKFRAME) {
                cltView->setPosition(0, 0, true);
            } else {
                cltView->setPosition(0, _ngux_phonebar_h, true);
            }
        }
    }

    m_isFullScreen = bfullScreen;

    refreshIndicator();
}

void ActivityWithBars::setFullScreen(bool bfullScreen, bool bhidemenubar)
{
    m_menuBarShown = !bhidemenubar;
    setFullScreen(bfullScreen);
}

void ActivityWithBars::exitHome(void)
{
    BaseActivity *app = NULL;
    ActivityManager *am = ActivityManager::getInstance();
    if (NULL != am) {
        BaseActivity* launcher = am->getActivityByName("launcher");
        if (launcher == NULL){
            return;
        }

        while ( (app = am->getCurrentActivity()) != NULL && app != launcher) {
            if(((ActivityWithBars *)app)->onEndKeyHome())
                app->exit();
            else
                break;
        }

        if((am->getCurrentActivity()) == launcher)
            ((ActivityWithBars *)launcher)->onEndKeyHome();

        return;
    }

    return;
}

void ActivityWithBars::exitCall(void)
{
    BaseActivity *app = NULL;
    ActivityManager *am = ActivityManager::getInstance();
    if (NULL != am) {
        BaseActivity* launcher = am->getActivityByName("launcher");
        BaseActivity* call = am->getActivityByName("call");

        if (launcher == NULL || call == NULL) {
            return;
        }

        while ( (app = am->getCurrentActivity()) != NULL && app != call) {
            if(((ActivityWithBars *)app)->onEndKeyHome())
                app->exit();
            else
                break;
        }

        return;
    }

    return;
}

bool ActivityWithBars::doCommand(int cmd)
{
    switch(cmd) {
        case APP_CMD_EXIT:
            exit();
            break;
        case APP_CMD_BACK:
            backView();
            break;
        case APP_CMD_OPEN_MENU:
            showMenu();
            break;
        case APP_CMD_OK:
            Profile::getInstance()->startPlayAudio(SAVE_TONE);
            if( 1 != backView(1) ) {//ok;
                if (!isFullScreen())
                    setFullScreen(false);
            }
            break;
        case APP_CMD_CANCEL:
            if( 1 != backView(0) ) {//cancel
                if (!isFullScreen())
                    setFullScreen(false);
            }
            break;
        default: {
            ControllerClient * client = getTop(0);
            if(client) {
                client->onControllerCommand(cmd, 0, 0);
            }
            break;
        }
    }
    return DISPATCH_STOP_MSG;
}

unsigned int ActivityWithBars::showView (int view_id,
        HTData param1, HTData param2)
{
    unsigned int ret = Activity::showView(view_id, param1, param2);
    if(ret == 1) {
        //maybe the client select cur app by exit() durning class(client) structure. but the cur client should be delete itself.
        //because the client dose not push stack. so controller can not manager it. if no delete it Manually. memory will be lost.
        return ret;
    }

    ActivityClient *clt = (ActivityClient *)getTop();
    if (NULL != clt) {
        View *cltView = clt->baseView();
        if (NULL != cltView) {
            if (!m_isFullScreen && view_id != APP_CLIENT_LOCKFRAME && !clt->isTip()){
                cltView->setPosition(0, _ngux_phonebar_h, true);
            }
            else {
                cltView->setPosition(0, 0, true);
            }

            if (clt->isTip()) {
                ActivityClient *_lower = NULL;
                for(int i = 1; (_lower = (ActivityClient *)getTop(i)) != NULL; i++){
                    _lower->baseView()->show();
                    if (!_lower->isTip()) {
                        break;
                    }
                }
                refreshMenubar();
            }
            else if (getClientCount() > 0) {
                refreshBars();
            }
        }
    }

    if (GetResourceLanguage() != m_usedLang) {
        m_usedLang = GetResourceLanguage();
        onLanguageChanged(m_usedLang);
    }

    return ret;
}

unsigned int ActivityWithBars::backView (unsigned int endCode)
{
    int ret;
    bool isExitFromLock = false;

    ActivityClient *_clt_top = (ActivityClient *)getTop(0);
    ActivityClient *_under = (ActivityClient *)getTop(1);

    if (_clt_top != NULL && _clt_top->isTip() && _under == NULL) {
        // only one tipdlg client
        // backview
        // don't exit...
        _clt_top->onBackView(endCode);
        _clt_top->inactive();
        if(m_modalCount > 0) {
            if(_clt_top && _clt_top->isModal()) {
                Window* window = SAFE_CAST(Window*, _clt_top->baseView()->rootView());
                window->endDlg(endCode);
                m_modalCount --;
            }
        }

        _clt_top->cleanBaseView();
        pop(1);
        return 0;
    }

    if (_clt_top == NULL) {
        return Activity::backView(endCode);
    }

    isExitFromLock = _clt_top->getId() == APP_CLIENT_LOCKFRAME;

    ret = Activity::backView(endCode);
    if (!ret) {
        if (GetResourceLanguage() != m_usedLang) {
            m_usedLang = GetResourceLanguage();
            onLanguageChanged(m_usedLang);
        }

        if (ActivityManager::getInstance()->getCurrentActivity() == this) {
            refreshBars();
        }
    }

    if (isExitFromLock) {
        onLockingExit();
    }

    return ret;
}

void ActivityWithBars::refreshBars (void)
{
    refreshIndicator();
    refreshMenubar();
}

void ActivityWithBars::refreshIndicator (void)
{
    if (m_indicator != NULL) {
        m_indicator->detachFromeViewTree(this);
        if (!m_isFullScreen) {
            m_indicator->addToViewTree(this);
        }
    }
}

void ActivityWithBars::refreshMenubar (void)
{
    if (m_menuBar != NULL) {
        m_menuBar->detachFromeViewTree(this);
        if (m_menuBarShown) {
            m_menuBar->addToViewTree(this);
        }
    }
}


void ActivityWithBars::onLanguageChanged(int langId)
{
    ControllerClientList::iterator it = m_list.begin();

    while(it != m_list.end()) {
        ControllerClient *_clt = (*it);
        if (_clt != NULL) {
            _clt->onControllerCommand(APP_CMD_REFRESH_TEXT, langId, 0);
        }
        it++;
    }
}

unsigned int ActivityWithBars::showTipView(int view_id, HTData param1, HTData param2)
{
    unsigned int ret = (unsigned int)-1;

    if (!m_tipShown) {
        m_tipShown = true;
        ret = showModalView(view_id, param1, param2);
        m_tipShown = false;
    }
    else {
        _ERR_PRINTF ("ActivityWithBars::showTipView: TipView re-entrance occurred\n");
    }

    return ret;
}

void ActivityWithBars::exitTip(int endCode)
{
    ActivityClient *_ctop = (ActivityClient *)getTop(0);

    if(_ctop != NULL && _ctop->isTip()) {
        if (ActivityManager::getInstance()->getCurrentActivity() == this) {
            backView(endCode);
        }
        else {
            deleteView(_ctop->getId());
        }
    }
}

ActivityClient *ActivityWithBars::getTopClient(bool bPop)
{
    int count = getClientCount();

    for (int i = 0; i < count; i++) {
        ActivityClient *_clt = (ActivityClient *)getTop(i);
        if ((bPop && _clt->isTip())
            || (!bPop && !_clt->isTip()))
            return _clt;
    }

    return NULL;
}

unsigned int ActivityWithBars::showMsgTipDlg(NGCPStr text_info, unsigned int type, int second)
{
    MsgTipDlgCreateInfo dlgcreate = {
        text_info,
        second,
        type,
    };

    return showTipView(TIPDLGAPP_CLIENT_ID_TIPDLG, (HTData )&dlgcreate, 0);
}

unsigned int ActivityWithBars::showMsgTextDlg(NGCPStr text_info, unsigned int type, int icon_id, int text_style, int second)
{
    MsgTextDlgCreateInfo dlgcreate = {
        text_info,
        second,
        icon_id,
        type,
        (bool)text_style
    };
    return showTipView(TIPDLGAPP_CLIENT_ID_TEXTDLG, (HTData )&dlgcreate, 0);
}

void ActivityWithBars::drawBackground(GraphicsContext* gc, IntRect &rc, int status)
{
    for (int i = 0; i < getClientCount(); i++) {
        ActivityClient *clt = (ActivityClient *)getTop(i);
        if (clt != NULL && !clt->isTip()) {
            Window::drawBackground (gc, rc, status);
            return;
        }
    }

    // If all the client are Tip client, should paint the Back Activity.
    if (ActivityManager::getInstance()->getCurrentActivity() == this) {
        Activity *app = (Activity *)(ActivityManager::getInstance()->getTopActivity(1));
        if (app != NULL) {
            int old = app->setLayer(1);
            IncludeWindowStyle((unsigned int)app->viewWindow(), WS_VISIBLE);
            ShowWindow((unsigned int)app->viewWindow(), SW_SHOWNORMAL);
            app->syncUpdateRect(rc.left(), rc.top(), rc.width(), rc.height(), false);
            ShowWindow((unsigned int)app->viewWindow(), SW_HIDE);
            setActiveWindow(viewWindow());
            app->setLayer(old);
        }
    }
}

void ActivityWithBars::onLockingShow(void)
{
    Menu *_m = menu();
    if (_m != NULL){
        _m->hideMenu();
        SetActiveWindow(viewWindow());
    }
}

void ActivityWithBars::onLockingExit(void)
{
    Menu *_m = menu();
    if (_m != NULL){
        _m->showMenu(this);
        SetActiveWindow(_m->viewWindow());
    }
}

bool ActivityWithBars::beInLockFrame(void)
{
    return find (APP_CLIENT_LOCKFRAME) != NULL;
}

unsigned int ActivityWithBars::showModalView(int view_id, HTData param1, HTData param2)
{
    if(view_id == APP_CLIENT_DELETE_CONFIRM) {
        MsgDlgCreateInfo dlgcreate = {
            GetTextRes(SS_DELETE_Q),
            0,//auto close time.
            MsgDlg::OKCANCELDLG
        };
        return Activity::showModalView (APP_CLIENT_MSGDLG, (HTData)&dlgcreate, 0);
    }
    else {
        return Activity::showModalView (view_id, param1, param2);
    }
}

MenuBarView* ActivityWithBars::getMenuBar()
{
    return m_menuBar->getMenuBar();
}

void ActivityWithBars::setCursor(int cursor_index, int current_value)
{
    common_menu_cursor[cursor_index] = current_value;
}

int ActivityWithBars::getCursor(int cursor_index)
{
    return common_menu_cursor[cursor_index];
}

#ifdef __SUPPORT_MANUAL_KEYPAD_LOCK_IN_ALLSCREEN__
void ActivityWithBars::setShowLockPopup (bool lockShow)
{
    m_isShowLockPopup = lockShow;
}
#endif

} // namespace hfcl
