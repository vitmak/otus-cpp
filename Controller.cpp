#include "Controller.h"


GraphicEditorApp::GraphicEditorApp() {
	m_drawingVisitor = new DrawingVisitor{};
}

void GraphicEditorApp::CreateNewDocument() {
	if (m_activeDoc && m_activeDoc->IsModified()) {
		// TODO: Save old document?
	}
	m_activeDoc = new Document{};
}

void GraphicEditorApp::ImportDocument(const std::string& filePath) {
	if (m_activeDoc && m_activeDoc->IsModified()) {
		// TODO: Save old document?
	}

	// Set new document
	// ...
	m_activeDoc->VisitAllPrimitives(m_drawingVisitor);
}

void GraphicEditorApp::ExportDocument(const std::string& filePath) {
	// Save the document
}

void GraphicEditorApp::CreatePrimitive(PrimitiveTypes primitiveType) {
	Primitive* shapePtr = nullptr;
	switch (primitiveType) {
	case PrimitiveTypes::ePoint:
		shapePtr = new Point{};
		break;
	
	case PrimitiveTypes::eLine:
		shapePtr = new Line{};
		break;
	
	case PrimitiveTypes::eCircle:
		shapePtr = new Circle{};
		break;
	
	case PrimitiveTypes::ePolygon:
		shapePtr = new Polygon{};
		break;
	
	default:
		// Unknown shape
		// ...
		break;
	}

	//SetShapeParam();
	m_activeDoc->AddPrimitive(shapePtr);
	shapePtr->Assept(m_drawingVisitor);
}

void GraphicEditorApp::DeletePrimitive() {
	if (m_activeDoc == nullptr || m_activeDoc->GetActiveShape() == nullptr)
		return;
	
	m_activeDoc->DeleteActivePrimitive();
	m_activeDoc->VisitAllPrimitives(m_drawingVisitor);
}

void GraphicEditorApp::SelectPrimitive(int x, int y) const {
	
	SelectingVisitor selectingVisitor(x, y);
	m_activeDoc->VisitAllPrimitives(&selectingVisitor);
	auto shapes = selectingVisitor.GetSelectedShapes();
	// ...
	Primitive* selectedShape = nullptr;
	// Select a specific shape from the 'shapes' list by any criterion.

	m_activeDoc->SetActiveShape(selectedShape);
}

void GraphicEditorApp::SetShapeParam(const std::vector<Point>& points) {

}
