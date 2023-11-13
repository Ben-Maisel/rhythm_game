#include "view.hxx"
static ge211::Color const white {255, 255,255};
static ge211::Color const gray {169,169,169};
View::View(Model const& model)
        : model_(model),
            white_circle(model_.radius, white),
          gray_circle(model_.radius, gray)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    if (model_.game_over()) {
      //draw endscreen sprites, display accuracy and score, number of 300s,
      // 200s, 100s, misses, etc.
    }
    else {//add receptor sprites
        set.add_sprite(gray_circle, model_.recep1.pos, 1);
        set.add_sprite(gray_circle, model_.recep2.pos, 1);
        set.add_sprite(gray_circle, model_.recep3.pos, 1);
        set.add_sprite(gray_circle, model_.recep4.pos, 1);

        for (Model::object obj: model_.objects) {
            set.add_sprite(white_circle, obj.pos, 0);
        }
        //add combo sprite here
        //add accuracy sprite here
        //add score sprite here
        //hit window sprites
        if (model_.object_hit) {
            if (model_.time_since_hit < .3) { //only show sprite for .3 second
                if (model_.hit_obj_val == 300) {
                    //add perfect sprite
                }
                else if (model_.hit_obj_val == 200) {
                    //add great sprite
                }
                else if (model_.hit_obj_val == 100) {
                    //add okay sprite
                }
                else if (model_.hit_obj_val == 0) {
                    //add miss sprite
                }
            }
        }
    }
}

Dimensions
View::screen_dims() const
{
    return {model_.screen_width, model_.screen_height};
}

std::string
View::window_title() const
{
    return "Rhythm Mania";
}