// ============================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_widget_focus.h
// package       : Qt_widget
// author(s)     : Radu Ursu
// release       : 
// release_date  : 
//
// coordinator   : Laurent Rineau <rineau@clipper.ens.fr>
//
// ============================================================================

#ifndef CGAL_QT_WIDGET_FOCUS_H
#define CGAL_QT_WIDGET_FOCUS_H


#include <CGAL/IO/pixmaps/focus1.xpm>
#include <CGAL/IO/pixmaps/focus1_mask.xpm>
#include <CGAL/IO/pixmaps/focus2.xpm>
#include <CGAL/IO/pixmaps/focus2_mask.xpm>
#include <CGAL/IO/pixmaps/focus3.xpm>
#include <CGAL/IO/pixmaps/focus3_mask.xpm>

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_layer.h>
#include <qcolor.h>
#include <qtimer.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qcursor.h>


namespace CGAL {

class Qt_widget_focus : public Qt_widget_layer
{
private:
  int     x2, y2;
  QPixmap *mouse_ico1,
          *mouse_ico2,
          *mouse_ico3;
  QCursor *cursor1,
          *cursor2,
          *cursor3;
  QBitmap cb, cm;
  int	  cycle;
  QCursor oldcursor;

public:
  Qt_widget_focus() : cycle(0) {
	mouse_ico1 = new QPixmap( (const char**)focus1_xpm);
	mouse_ico2 = new QPixmap( (const char**)focus2_xpm);
	mouse_ico3 = new QPixmap( (const char**)focus3_xpm);
	
	QPixmap *mouse_ico_mask1 = new QPixmap((const char**)focus1_mask_xpm);	
	QPixmap *mouse_ico_mask2 = new QPixmap((const char**)focus2_mask_xpm);
	QPixmap *mouse_ico_mask3 = new QPixmap((const char**)focus3_mask_xpm);

	cb = *mouse_ico1; cm = *mouse_ico_mask1;
	mouse_ico1->setMask(cm);
	cursor1 = new QCursor(*mouse_ico1);

	cb = *mouse_ico2; cm = *mouse_ico_mask2;
	mouse_ico2->setMask(cm);
	cursor2 = new QCursor(*mouse_ico2);

	cb = *mouse_ico3; cm = *mouse_ico_mask3;
	mouse_ico3->setMask(cm);
	cursor3 = new QCursor(*mouse_ico3);
  };

  void timerEvent( QTimerEvent *e )
  {
	switch(cycle){
	case 1:
		widget->setCursor(*cursor1);
		cycle++;
		break;
	case 2:
		widget->setCursor(*cursor2);
		cycle++;
		break;
	case 3:
		widget->setCursor(*cursor3);
		cycle=1;
		break;
	}
  }
private:
  bool is_pure(Qt::ButtonState s){
    if((s & Qt::ControlButton) ||
       (s & Qt::ShiftButton) ||
       (s & Qt::AltButton))
      return 0;
    else
      return 1;
  }
  void mousePressEvent(QMouseEvent *e)
  {
    if(e->button() == Qt::LeftButton
       && is_pure(e->state()))
    {
      double x, y;
      widget->x_real(e->x(), x);
      widget->y_real(e->y(), y);	
      widget->set_center(x, y);
    }
  };
  void deactivating()
  {    
    widget->setCursor(oldcursor);
	  killTimers();
  };

  void activating()
  {
    oldcursor = widget->cursor();
	  startTimer( 200 );
	  cycle = 1;

  };
};//end class 

} // namespace CGAL

#endif // CGAL_QT_WIDGET_FOCUS_H
