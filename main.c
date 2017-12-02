#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int red;
  int green;
  int blue;
} Color;

char * color_to_hex(Color *color) {

  // The output should be 6 chars plus the null terminator
  char *hex = malloc(7);

  // Write each of the ints of the color to the string as hex values
  sprintf(hex, "%02x%02x%02x", color->red, color->green, color->blue);
  return hex;
}

char * percent_to_hex(double percent) {
  // We can only handle 0-100%
  if (percent > 1.0) { percent = 1.0; }
  if (percent < 0) { percent = 0; }

  Color c = { 0, 0, 0 };

  // If the percentage is above 50%, the green should be maxed out, and we
  // increase the red value the lower the percentage.
  // The inverse is true below 50%
  if (percent >= 0.5) {
    c.red = 255 * 2 * (1 - percent);
    c.green = 255;
  } else {
    c.red = 255;
    c.green = 255 * 2 * percent;
  }

  return color_to_hex(&c);
}

int main(int argc, char ** argv) {
  if (argc == 2) {
    double input = atof(argv[1]);

    // If we receive a number not between 0 and 1, it's probably a percent as in
    // 50%. Divide it by 100 to get it into our format.
    if (input > 1) {
      input = input / 100.0;
    }

    printf("#%s", percent_to_hex(input));
  }
  return 0;
}
