#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

G_BEGIN_DECLS

#include <stdint.h>
#include <cairo.h>
#include "runtime.h"

class Transform : public DependencyObject {
 protected:
 	Transform () { }
	Value::Kind GetObjectType () { return Value::TRANSFORM; };
 public:
	virtual void OnPropertyChanged (DependencyProperty *prop);
	virtual void GetTransform (cairo_matrix_t *value) = 0;
};

void   transform_get_transform (Transform *t, cairo_matrix_t *value);

class RotateTransform : public Transform {
 public:

	RotateTransform () { }
	Value::Kind GetObjectType () { return Value::ROTATETRANSFORM; };

	static DependencyProperty* AngleProperty;
	static DependencyProperty* CenterXProperty;
	static DependencyProperty* CenterYProperty;

	virtual void GetTransform (cairo_matrix_t *value);
};

RotateTransform * rotate_transform_new ();

void   rotate_transform_set_angle (RotateTransform *t, double angle);
double rotate_transform_get_angle (RotateTransform *t);

void   rotate_transform_set_center_x (RotateTransform *t, double centerX);
double rotate_transform_get_center_x (RotateTransform *t);

void   rotate_transform_set_center_y (RotateTransform *t, double centerY);
double rotate_transform_get_center_y (RotateTransform *t);

class TranslateTransform : public Transform {
 public:

	TranslateTransform () {  }
	Value::Kind GetObjectType () { return Value::TRANSLATETRANSFORM; };

	static DependencyProperty* XProperty;
	static DependencyProperty* YProperty;

	virtual void GetTransform (cairo_matrix_t *value);
};

TranslateTransform *translate_transform_new ();
void   translate_transform_set_x (TranslateTransform *t, double x);
double translate_transform_get_x (TranslateTransform *t);

void   translate_transform_set_y (TranslateTransform *t, double y);
double translate_transform_get_y (TranslateTransform *t);


class ScaleTransform : public Transform {
public:

	ScaleTransform () {  }
	Value::Kind GetObjectType () { return Value::SCALETRANSFORM; };

	static DependencyProperty* ScaleXProperty;
	static DependencyProperty* ScaleYProperty;
	static DependencyProperty* CenterXProperty;
	static DependencyProperty* CenterYProperty;

	virtual void GetTransform (cairo_matrix_t *value);
};

ScaleTransform * scale_transform_new ();
void   scale_transform_set_scale_x (ScaleTransform *t, double scaleX);
double scale_transform_get_scale_x (ScaleTransform *t);

void   scale_transform_set_scale_y (ScaleTransform *t, double scaleY);
double scale_transform_get_scale_y (ScaleTransform *t);

void   scale_transform_set_center_x (ScaleTransform *t, double centerX);
double scale_transform_get_center_x (ScaleTransform *t);

void   scale_transform_set_center_y (ScaleTransform *t, double centerY);
double scale_transform_get_center_y (ScaleTransform *t);


class MatrixTransform : public Transform {
 public:

	MatrixTransform () { }
	Value::Kind GetObjectType () { return Value::MATRIXTRANSFORM; };

	/* these are dependency properties
	   Matrix matrix;
	*/

	virtual void GetTransform (cairo_matrix_t *value);
};

MatrixTransform *matrix_transform_new ();
void           matrix_transform_set_matrix (MatrixTransform *t, cairo_matrix_t matrix);
cairo_matrix_t matrix_transform_get_matrix (MatrixTransform *t);


class TransformCollection : public Collection {
 public:
	TransformCollection () {}
	virtual Value::Kind GetObjectType () { return Value::TRANSFORM_COLLECTION; }

	virtual void Add    (void *data);
	virtual void Remove (void *data);
};

class TransformGroup : public Transform {
public:
	static DependencyProperty* ChildrenProperty;

	TransformCollection *children;
	
	TransformGroup ();
	Value::Kind GetObjectType() { return Value::TRANSFORMGROUP; };

	
	virtual void OnPropertyChanged (DependencyProperty *prop);
	virtual void GetTransform (cairo_matrix_t *value);
};

G_END_DECLS

#endif
