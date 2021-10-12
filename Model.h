#pragma once

#include <vector>
#include <string>
#include <forward_list>


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

	void AddPrimitive(Primitive* shapePtr) {
		m_shapes.push_front(shapePtr);
		// ...
		m_pActiveShape = shapePtr;
		m_isModified = true;
	}

	void DeleteActivePrimitive() {
		if (m_pActiveShape == nullptr)
			return;
		
		// Delete the active shape from 'm_shapes'
		// ...
		m_pActiveShape = nullptr;
		m_isModified = true;
	}

	void VisitAllPrimitives(IShapeVisitor* visitor) const {
		for (const auto v : m_shapes) {
			v->Assept(visitor);
		}
	}

	bool IsModified() const {
		return m_isModified;
	}

	Primitive* GetActiveShape() const {
		return m_pActiveShape;
	}

private:
	std::string m_filePath;
	bool m_isModified;
	Primitive* m_pActiveShape = nullptr;

	std::forward_list<Primitive*> m_shapes;
};
