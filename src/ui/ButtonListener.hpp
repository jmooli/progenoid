#pragma once

class ButtonListener {
public:
  virtual ~ButtonListener() = default;
  virtual void onButtonPressed() = 0;
};
