#ifndef POS_H
#define POS_H

struct Pos {
public:
    int x, y;

    Pos(int _x=-1, int _y=-1);
    Pos(const Pos& _p) ;

    bool operator== (Pos _p);
    bool operator!= (Pos _p);
    bool operator< (Pos _p);
    bool operator<= (Pos _p);
    bool operator> (Pos _p);
    bool operator>= (Pos _p);
    Pos operator+ (Pos _p);
    Pos operator- (Pos _p);
    Pos operator* (int k);
    void operator+= (Pos _p);
    void operator-= (Pos _p);
    void operator*= (int k);
    Pos operator++ ();
    Pos operator-- ();

    void setMaxY(int _maxY);

private:
    int maxY;
};

#endif // POS_H

