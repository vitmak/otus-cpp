#include "Model.h"


void Point::Assept(std::shared_ptr<IShapeVisitor> visitorPtr) {
	visitorPtr->VisitPoint(*this);
}

void Line::Assept(std::shared_ptr<IShapeVisitor> visitorPtr) {
	visitorPtr->VisitLine(*this);
}

void Circle::Assept(std::shared_ptr<IShapeVisitor> visitorPtr) {
	visitorPtr->VisitCircle(*this);
}

void Polygon::Assept(std::shared_ptr<IShapeVisitor> visitorPtr) {
	visitorPtr->VisitPolygon(*this);
}