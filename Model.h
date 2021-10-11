#pragma once

#include <vector>
#include <string>

class IShapeVisitor;

class Primitive {
public:
	virtual void Assept(IShapeVisitor* VisitorPtr) = 0;
};

class Point : public Primitive {
public:
	void Assept(IShapeVisitor* VisitorPtr) override;

private:
	int m_x;
	int m_y;
};

class Line : public Primitive {
public:
	void Assept(IShapeVisitor* VisitorPtr) override;

private:
	Point m_start;
	Point m_end;
};

class Circle : public Primitive {
public:
	void Assept(IShapeVisitor* VisitorPtr) override;

private:
	Point m_center;
	double m_radius;
};

class Polygon : public Primitive {
public:
	void Assept(IShapeVisitor* VisitorPtr) override;

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
	Document() = default;

	void AddPrimitive(Primitive* shapePtr) {}
	void DeletePrimitive(Primitive* shapePtr);

	void VisitAllPrimitives() const;


	bool IsModified() const {
		return m_isModified;
	}

private:
	std::string m_filePath;
	bool m_isModified;
	Primitive* m_pActiveShape = nullptr;
};
