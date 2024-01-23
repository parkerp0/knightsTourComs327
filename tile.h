typedef struct tile tile;

struct tile
{
    int num;
    int visit;
    int jumpc;
    tile **jump;
};