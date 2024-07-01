#ifndef COORD_H
#define COORD_H

class coord {
public:
    int x;
    int y;

    coord() {}
    coord(int xx, int yy) : x{xx}, y{yy} {}

    bool valida() {
        return (x < 8 && x >= 0 && y < 8 && y >= 0);
    }

    bool operator==(const coord& o) {
        return (x == o.x) && (y == o.y);
    }

    bool operator!=(const coord& o) {
        return !(*this == o);
    }

    coord operator-(const coord& o) {
        return {x - o.x, y - o.y};
    }

    coord operator+(const coord& o) {
        return {x + o.x, y + o.y};
    }

    bool operator<(const coord& o) {
        return (x < o.x) || (x == o.x && y < o.y);
    }
    
    friend bool operator<(const coord& a, const coord& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    }
};


#endif // COORD_H