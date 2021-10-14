#pragma once

#include <vector>
#include <string>
#include <forward_list>
#include <memory>


class IShapeVisitor;

class Primitive {
public:
	virtual void Assept(std::shared_ptr<IShapeVisitor> VisitorPtr) = 0;
};

class Point : public Primitive {
public:
	void Assept(std::shared_ptr<IShapeVisitor> VisitorPtr) override;

private:
	int m_x;
	int m_y;
};

class Line : public Primitive {
public:
	void Assept(std::shared_ptr<IShapeVisitor> VisitorPtr) override;

private:
	Point m_start;
	Point m_end;
};

class Circle : public Primitive {
public:
	void Assept(std::shared_ptr<IShapeVisitor> VisitorPtr) override;

private:
	Point m_center;
	double m_radius;
};

class Polygon : public Primitive {
public:
	void Assept(std::shared_ptr<IShapeVisitor> VisitorPtr) override;

private:
	std::vector<Point> m_points;
};

// The GoF Visitor pattern
class IShapeVisitor {
public:
	virtual void VisitPoint(const Point& point) = 0;
	virtual void VisitLine(const Line& line) = 0;
	virtual void VisitCircle(const Circle& circle) = 0;
	virtual void VisitPolygon(const Polygon& polygon) = 0;
};

class Document {
public:
	Document() = default;

	void AddPrimitive(std::shared_ptr<Primitive> shapePtr) {
		m_shapes.push_front(shapePtr);
		// ...
		m_activeShapePtr = shapePtr;
		m_isModified = true;
	}

	void DeleteActivePrimitive() {
		if (m_activeShapePtr == nullptr)
			return;
		
		// Delete the active shape from 'm_shapes'
		// ...
		m_activeShapePtr.reset();
		m_isModified = true;
	}

	void VisitAllPrimitives(std::shared_ptr<IShapeVisitor> visitor) const {
		for (const auto v : m_shapes) {
			v->Assept(visitor);
		}
	}

	bool IsModified() const {
		return m_isModified;
	}

	std::shared_ptr<Primitive> GetActiveShape() const {
		return m_activeShapePtr;
	}

	void SetActiveShape(Primitive* primitivePtr){	
	    //...
	}

private:
	std::string m_filePath;
	bool m_isModified = false;

	std::shared_ptr<Primitive> m_activeShapePtr;
	std::forward_list<std::shared_ptr<Primitive>> m_shapes;
};
