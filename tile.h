

typedef struct tile_t
{
    int num;
    int visit;
    int jumpc;
    struct tile **jump;
}tile;
