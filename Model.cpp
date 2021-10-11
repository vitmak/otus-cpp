#include "Model.h"

void Point::Assept(ShapeVisitor* visitorPtr) {
	visitorPtr->VisitPoint(this);
}

void Line::Assept(ShapeVisitor* visitorPtr) {
	visitorPtr->VisitLine(this);
}

void Circle::Assept(ShapeVisitor* visitorPtr) {
	visitorPtr->VisitCircle(this);
}

void Polygon::Assept(ShapeVisitor* visitorPtr) {
	visitorPtr->VisitPolygon(this);
}