#pragma once

#include "Model.h"
#include "View.h"
#include "string"


class DrawingVisitor : public IShapeVisitor {
public:
	DrawingVisitor() = default;

	void VisitPoint(Primitive* shapePtr) override {
		// Draw point
	}
	void VisitLine(Primitive* shapePtr) override {
		// Draw line
	}
	void VisitCircle(Primitive* shapePtr) override {
		// Draw circle
	}
	void VisitPolygon(Primitive* shapePtr) override {
		// Draw polygon
	}

private:
	Canvas* m_canvasPtr;
};

// The class contains shapes that contain specified point. Used to select shapes.
class SelectingVisitor : public IShapeVisitor {
public:
	SelectingVisitor(int x, int y) : m_x{x}, m_y{y} {}

	std::forward_list<Primitive*> GetSelectedShapes() const {
		//...
		return m_selectedShapes;
	}

	void VisitPoint(Primitive* shapePtr) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}
	void VisitLine(Primitive* shapePtr) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}
	void VisitCircle(Primitive* shapePtr) override {
		// Check if the shape contains a coordinate, then add the shape to the list 'm_selectedShapes'.
	}
	void VisitPolygon(Primitive* shapePtr) override {
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
	Document* m_activeDoc = nullptr;
	DrawingVisitor* m_drawingVisitor;
	
	EditorFrame m_EditorFrame;
};
