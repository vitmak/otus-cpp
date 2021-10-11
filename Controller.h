#pragma once

#include "Model.h"


class std::string;
class Document;
class Canvas;

enum class PrimitiveTypes {
	eLine = 0,
	eRectangle,
	eCircle
};

class IShapeVisitor {
public:
	virtual void VisitPoint(Primitive* shapePtr) = 0;
	virtual void VisitLine(Primitive* shapePtr) = 0;
	virtual void VisitCircle(Primitive* shapePtr) = 0;
	virtual void VisitPolygon(Primitive* shapePtr) = 0;
};

class DrawingVisitor : public IShapeVisitor {
public:
	DrawingVisitor() = default;

	virtual void VisitPoint(Primitive* shapePtr) = 0;
	virtual void VisitLine(Primitive* shapePtr) = 0;
	virtual void VisitCircle(Primitive* shapePtr) = 0;
	virtual void VisitPolygon(Primitive* shapePtr) = 0;

private:
	//Canvas* m_canvasPtr;
	Canvas m_canvas;
};

class GraphicEditorApp {
public:
	GraphicEditorApp();
	~GraphicEditorApp();
	void CreateNewDocument();

	void ImportDocument(const std::string& path);
	void ExportDocument(const std::string& path);

	void CreatePrimitive(const EPrimitiveTypes::eCircle, int primitiveID);
	void DeletePrimitive(int primitiveID);

	Primitive* SelectPrimitive(int primitiveID) const;

	//void SaveAs(); // convert document to XML / JSON format
	//void PrintDocument() const;

private:
	void SetShapeParam(const std::vector<Point>& points);

	Document* m_activeDoc = nullptr;
	DrawingVisitor m_drawingVisitor;
};