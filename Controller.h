#pragma once

#include "Model.h"
#include "string"


class Document;
class Canvas;

enum class PrimitiveTypes {
	ePoint = 0,
	eLine,
	eCircle,
	ePolygon
};

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

class GraphicEditorApp {
public:
	GraphicEditorApp() = default;
	//~GraphicEditorApp();
	
	void CreateNewDocument();

	void ImportDocument(const std::string& filePath);
	void ExportDocument(const std::string& filePath);

	void CreatePrimitive(PrimitiveTypes primitiveType, int primitiveID);
	void DeletePrimitive(Primitive* primitivePtr);

	Primitive* SelectPrimitive(int primitiveID) const;

	//void SaveAs(); // convert document to XML / JSON format
	//void PrintDocument() const;

private:
	void SetShapeParam(const std::vector<Point>& points);

	Document* m_activeDoc = nullptr;
	DrawingVisitor* m_drawingVisitor;
};