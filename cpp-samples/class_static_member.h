class example {
    static int count;
public:
    static int get_count ();

public:

    /* you can set val2 here, or at definition */
    static const int val2;

    /* must give a default value */
    static constexpr int val3 = 30;
};


