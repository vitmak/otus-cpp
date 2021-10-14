#include "Controller.h"


GraphicEditorApp::GraphicEditorApp() {
	m_drawingVisitorPtr = std::make_shared<DrawingVisitor>(m_EditorFrame.GetCanvas());
}

void GraphicEditorApp::CreateNewDocument() {
	if (m_activeDocPtr && m_activeDocPtr->IsModified()) {
		// TODO: Save old document?
	}
	m_activeDocPtr = std::make_unique<Document>(Document{});
}

void GraphicEditorApp::ImportDocument(const std::string& filePath) {
	if (m_activeDocPtr && m_activeDocPtr->IsModified()) {
		// TODO: Save old document?
	}

	// Set new document
	// ...
	m_activeDocPtr->VisitAllPrimitives(m_drawingVisitorPtr);
}

void GraphicEditorApp::ExportDocument(const std::string& filePath) {
	// Save the document
}

void GraphicEditorApp::CreatePrimitive(PrimitiveTypes primitiveType) {
	std::shared_ptr<Primitive> shapePtr;
	switch (primitiveType) {
	case PrimitiveTypes::ePoint:
		shapePtr = std::make_shared<Point>(Point{});
		break;
	
	case PrimitiveTypes::eLine:
		shapePtr = std::make_shared<Line>(Line{});
		break;
	
	case PrimitiveTypes::eCircle:
		shapePtr = std::make_shared<Circle>(Circle{});
		break;
	
	case PrimitiveTypes::ePolygon:
		shapePtr = std::make_shared<Polygon>(Polygon{});
		break;
	
	default:
		// Unknown shape
		// ...
		break;
	}

	m_activeDocPtr->AddPrimitive(shapePtr);
	shapePtr->Assept(m_drawingVisitorPtr);
}

void GraphicEditorApp::DeletePrimitive() {
	if (m_activeDocPtr == nullptr || m_activeDocPtr->GetActiveShape() == nullptr)
		return;
	
	m_activeDocPtr->DeleteActivePrimitive();
	m_activeDocPtr->VisitAllPrimitives(m_drawingVisitorPtr);
}

void GraphicEditorApp::SelectPrimitive(int x, int y) const {
	auto selectingVisitor = std::make_shared<SelectingVisitor>(x, y);
	m_activeDocPtr->VisitAllPrimitives(selectingVisitor);
	auto shapes = selectingVisitor->GetSelectedShapes();
	// ...
	Primitive* selectedShape = nullptr;
	// Select a specific shape from the 'shapes' list by any criterion.

	m_activeDocPtr->SetActiveShape(selectedShape);
}
