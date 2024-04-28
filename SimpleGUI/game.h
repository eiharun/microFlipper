
typedef enum {UP,DOWN} dirud;
typedef enum {LEFT,RIGHT} dirlr;
struct _pong{
  int x_pos;
  int y_pos;
  int w_size;
  int h_size;
  dirud directionud;
  dirlr directionlr;

}; typedef struct _pong pong;
