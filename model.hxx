#pragma once

#include <ge211.hxx>
#include <vector>
using Dimensions = ge211::Dims<int>;
using Position = ge211::Posn<int>;
class Model
{
public:
    const static int radius = 70;
    const int screen_height = 720;
    const int screen_width = 1280;
private:
    double song_length = 150; //2:30 minutes
    double time_passed;
    const int column_width = 600;
    const Position receptor1 = {(screen_width-column_width)/2,
                                screen_height-radius-5};
    const Position receptor2 = {(screen_width-column_width)/2 + column_width/4,
                                screen_height-radius-5};
    const Position receptor3 = {(screen_width-column_width)/2 +
                                2*column_width/4, screen_height-radius-5};
    const Position receptor4 = {(screen_width-column_width)/2 +
                                3*column_width/4, screen_height-radius-5};
public:
    struct object {
        Position pos;
        object(Position pos2); //top left corner position
        Position center = {pos.x+radius, pos.y+radius};
    };
    object recep1;
    object recep2;
    object recep3;
    object recep4;
    std::vector<object> objects;
    std::vector<int> score_array;
    int score;
    float accuracy;
    const int obj_speed = 360; //360 pixels per second
    void on_frame(double dt);
    int combo;
    void on_hit(object receptor);
    bool game_over() const;
    bool start_menu() const;
    bool object_hit = false;
    double time_since_hit;
    int hit_obj_val;
    explicit Model();
private:
    const int perfect = 15; //pixels
    const int great = 22;
    const int okay = 26;
    const int miss = 32;
    int frame;

    void calc_points(object receptor, object obj);
    void delete_obj(object obj);
    float calc_accuracy();
    bool fall_below_screen(object obj);
    void generate_objects(object receptor);
    void generate_map(int frame);
    bool game_over();
    int calc_total_score();
};

