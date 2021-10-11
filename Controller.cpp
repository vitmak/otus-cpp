#include "Controller.h"


void GraphicEditorApp::CreateNewDocument() {
	if (m_activeDoc && m_activeDoc->IsModified()) {
		// ������� ������ � ��������, ��������� ����������� ��� ��� ...

	}
	m_activeDoc = new Document{};
}

void GraphicEditorApp::ImportDocument(const std::string& filePath) {

}

void GraphicEditorApp::ExportDocument(const std::string& filePath) {

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
		// use throw ("Unknown shape");
		break;
	}

	//SetShapeParam();
	m_activeDoc->AddPrimitive(shapePtr);
	shapePtr->Assept(m_drawingVisitor);
}

void GraphicEditorApp::DeletePrimitive(Primitive* primitivePtr) {

}

Primitive* GraphicEditorApp::SelectPrimitive(int primitiveID) const {
	// ...
	return nullptr;
}

//void SaveAs(); // convert document to XML / JSON format
//void PrintDocument() const;

void GraphicEditorApp::SetShapeParam(const std::vector<Point>& points) {

}