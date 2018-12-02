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


#ifndef _NGUX_ContainerView_h
#define _NGUX_ContainerView_h

#include "view.h"

NAMESPACE_BEGIN

class ContainerView : public View {
    public:
		ContainerView();
        ContainerView(View* parent);
        ContainerView(View* parent, DrawableSet* dr);
		ContainerView(int id, int x, int y, int w, int h);
		virtual ~ContainerView();

		bool isChild(View* view) const;
		bool insertBefore(View *view, View *child);
		bool insertAfter(View *view, View *child);
		bool insertBefore(int idx, View* child);
		bool insertAfter(int idx, View* child) { return (child) ? insertAfter(getChildByIndex(idx), child) : false; }

		bool addChild(View* child) { return insertAfter(m_lastChild, child); }
		bool addChildHead(View* child) { return insertBefore(m_firstChild, child); }
        // by default , we delete the child, but NOT when bRelease = false
		int  removeChild(View* child, bool bRelease = true);
        // by default , we delete the child, but NOT when bRelease = false
		int  removeChild(int index, bool bRelease = true);
		int  removeAll();
		int  detachChild(View* child);
		int  detachChild(int child);
		void clean();

		View* getChild(int id) const;
		View* getChildByIndex(int idx) const;
		View* getView (int id) const;
		int   getChildIndex(View *view) const;
		View *getChildByPosition(int x_pos, int y_pos) const;

		View* firstChild(void) const { return m_firstChild;}
        View* firstEnableChild(void);
		View* lastChild(void) const { return m_lastChild;}
		int  viewCount(void) const { return m_childCount;}

		virtual void changeTheme(void);
		bool isContainerView(void) { return true; }
		void setFocusView(View* view);
		void releaseFocusView(void);
		View* focusView(void) const { return m_focusView;}
		virtual void drawBackground(GraphicsContext* context, IntRect &rc, int status /*= Style::NORMAL*/);
		virtual void drawContent(GraphicsContext *context, IntRect &rc, int status/* = Style::NORMAL*/);
		virtual bool dispatchEvent(Event* event);

		virtual void autoFitSize(bool auto_child_fit = false);

		virtual void onChildSizeChanged(View* child) { 
			if(isAutoSize()) {
				autoFitSize();
				if(parent())
					parent()->onChildSizeChanged(this);
			}
		}

    protected:
		View *m_focusView;
		View *m_firstChild;
		View *m_lastChild;
		int   m_childCount;

		enum {
			AUTOSIZE = (1 << View::FLAG_SHIFT),
			FLAG_SHIFT = (View::FLAG_SHIFT + 1)
		};

	DECLARE_CLASS_NAME(ContainerView)

	public:

		void setAutoSize(bool b) { setFlag(b, AUTOSIZE); }
		bool isAutoSize(void) { return m_flags & AUTOSIZE; }
};

NAMESPACE_END

#endif /* NGUX_ContainerView_h */
