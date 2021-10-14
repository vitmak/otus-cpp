#pragma once

#include "Model.h"
#include "View.h"
#include <string>
#include <memory>


class DrawingVisitor : public IShapeVisitor {
public:
	DrawingVisitor(std::shared_ptr<Canvas> canvas) : m_canvasPtr{ canvas } {}

	void VisitPoint(const Point& point) override {
		// Draw point
	}
	void VisitLine(const Line& line) override {
		// Draw line
	}
	void VisitCircle(const Circle& circle) override {
		// Draw circle
	}
	void VisitPolygon(const Polygon& polygon) override {
		// Draw polygon
	}

private:
	std::shared_ptr<Canvas> m_canvasPtr;
};

// The class contains shapes that contain specified point. Used to select shapes.
class SelectingVisitor : public IShapeVisitor {
public:
	SelectingVisitor(int x, int y) : m_x{x}, m_y{y} {}

	std::forward_list<Primitive*> GetSelectedShapes() const {
		//...
		return m_selectedShapes;
	}

	void VisitPoint(const Point& point) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}
	void VisitLine(const Line& line) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}
	void VisitCircle(const Circle& circle) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}
	void VisitPolygon(const Polygon& polygon) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}

private:
	int m_x;
	int m_y;

	std::forward_list<Primitive*> m_selectedShapes;
};

class Document;
class GraphicEditorApp {
public:
	GraphicEditorApp();
	
	void CreateNewDocument();

	void ImportDocument(const std::string& filePath);
	void ExportDocument(const std::string& filePath);

	void CreatePrimitive(PrimitiveTypes primitiveType);
	void DeletePrimitive();

	void SelectPrimitive(int x, int y) const;


	const EditorFrame& GetFrame() const {
		return m_EditorFrame;
	}

private:
	std::unique_ptr<Document> m_activeDocPtr;
	std::shared_ptr<DrawingVisitor> m_drawingVisitorPtr;
	
	EditorFrame m_EditorFrame;
};
