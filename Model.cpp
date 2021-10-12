#include "Model.h"


void Point::Assept(IShapeVisitor* visitorPtr) {
	visitorPtr->VisitPoint(this);
}

void Line::Assept(IShapeVisitor* visitorPtr) {
	visitorPtr->VisitLine(this);
}

void Circle::Assept(IShapeVisitor* visitorPtr) {
	visitorPtr->VisitCircle(this);
}

void Polygon::Assept(IShapeVisitor* visitorPtr) {
	visitorPtr->VisitPolygon(this);
}