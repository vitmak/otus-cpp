#pragma once

#include <vector>
#include <string>

class ShapeVisitor;

class Shape {
public:
	virtual void Assept(ShapeVisitor * VisitorPtr) = 0;
};

class Point : public Shape {
public:
	void Assept(ShapeVisitor* VisitorPtr) override;

private:
	int m_x;
	int m_y;
};

class Line : public Shape {
public:
	void Assept(ShapeVisitor* VisitorPtr) override;

private:
	Point m_start;
	Point m_end;
};

class Circle : public Shape {
public:
	void Assept(ShapeVisitor* VisitorPtr) override;

private:
	Point m_center;
	double m_radius;
};

class Polygon : public Shape {
public:
	void Assept(ShapeVisitor* VisitorPtr) override;

private:
	std::vector<Point> m_points;
};

// The GoF Visitor pattern
class IShapeVisitor {
public:
	virtual void VisitPoint(Primitive* shapePtr) = 0;
	virtual void VisitLine(Primitive* shapePtr) = 0;
	virtual void VisitCircle(Primitive* shapePtr) = 0;
	virtual void VisitPolygon(Primitive* shapePtr) = 0;
};

class Document {
public:
	Document(const std::string& filePath) = default;
	void AddPrimitive(Shape *shapePtr);
	void DeletePrimitive(Shape* shapePtr);
private:
	std::string m_filePath;
	bool m_isModified;
	Shape* m_pActiveShape = nullptr;
};
