#pragma once

struct GuiMargin
{

public:

  GuiMargin(float topMargin = 12.f,
            float rightMargin = 4.f,
            float bottomMargin = 12.f,
            float leftMargin = 4.f) 
            : top(topMargin), 
              right(rightMargin), 
              bottom(bottomMargin), 
              left(leftMargin) { }

  ~GuiMargin() {}

  void SetMargins(float topMargin, float rightMargin, float bottomMargin, float leftMargin)
  {
    top = topMargin;
    right = rightMargin;
    bottom = bottomMargin;
    leftMargin = leftMargin;
  }

  void SetTopMargin(float topMargin)       { top = topMargin; }
  void SetRightMargin(float rightMargin)   { right = rightMargin; }
  void SetBottomMargin(float bottomMargin) { bottom = bottomMargin; }
  void SetLeftMargin(float leftMargin)     { left = leftMargin; }

  void GetMargins(float &topMargin, float &rightMargin, float &bottomMargin, float &leftMargin)
  {
    topMargin = top;
    rightMargin = right;
    bottomMargin = bottom;
    leftMargin = left;
  }

  float GetTopMargin() const    { return top; }
  float GetRightMargin() const  { return right; }
  float GetBottomMargin() const { return bottom; }
  float GetLeftMargin() const   { return left; }

  float &GetTopMargin()    { return top; }
  float &GetRightMargin()  { return right; }
  float &GetBottomMargin() { return bottom; }
  float &GetLeftMargin()   { return left; }

private:

  float top;
  float right;
  float bottom;
  float left;

};
