#pragma once
#include "model.hxx"
#include <string>
class View
{
public:

    explicit View(Model const&);
    void draw(ge211::Sprite_set& set);
    Dimensions screen_dims() const;
    std::string window_title() const;
private:
    Model const& model_;
    //SPRITES
    ge211::Circle_sprite const white_circle;
    ge211::Circle_sprite const gray_circle;
};