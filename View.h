#pragma once

class Document;

enum class PrimitiveTypes {
	ePoint = 0,
	eLine,
	eCircle,
	ePolygon,
	eEmpty
};


class Canvas {
public:
	Canvas() = default;
	void OnMouseButtonClick(){}
};

//
class Toolbar {
public:
	Toolbar() = default;

	void OnClickPrimitiveForm(PrimitiveTypes primitiveType) {
		// Activate creating primitive mode 
	}

	void OnClickColorPalette() {
		// Set color settings
	}

	// ...

private:
	PrimitiveTypes m_activeShapeType = PrimitiveTypes::eEmpty;
};

// TODO: add next classes:
// - class MenuItem{};
// - class Menu {};