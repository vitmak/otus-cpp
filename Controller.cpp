#include "Controller.h"


GraphicEditorApp::GraphicEditorApp() {
	m_drawingVisitor = 
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

void GraphicEditorApp::CreatePrimitive(PrimitiveTypes primitiveType, int primitiveID) {
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
	
	//auto shapes = m_activeDoc->GetShapes(x, y);
}

void GraphicEditorApp::SetShapeParam(const std::vector<Point>& points) {

}
