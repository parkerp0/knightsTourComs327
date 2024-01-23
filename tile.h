typedef struct tile tile;

typedef struct tile
{
    int num;
    int visit;
    int jumpc;
    tile **jump;
    tile **visited;
}tile;
