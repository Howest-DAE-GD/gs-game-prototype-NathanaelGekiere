#pragma once
class Key
{
public:
	Key(Rectf bounds, int uses, bool used, Color4f color, std::string colors);
	void Draw();
	void SetBounds(Rectf bounds);
	void UseKey();
	Rectf GetBounds() const;
	Color4f GetColor();
	std::string GetString();
private:
	Rectf m_Bounds;
	int m_uses;
	bool m_used;
	Color4f m_Color;
	std::string m_Colors;
};

