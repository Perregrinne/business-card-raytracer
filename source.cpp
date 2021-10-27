#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vector {
  float x, y, z;
  vector() {}
  vector(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
  }

  //Scaling operator
  vector operator*(float d) {
    return vector(d * x, d * y, d * z);
  }

  //Vector Addition operator
  vector operator+(vector v) {
    return vector(v.x + x, v.y + y, v.z + z);
  }

  //Dot Product operator
  float operator%(vector v) {
    return v.x * x + v.y * y + v.z * z;
  }

  //Cross Product operator
  vector operator^(vector v) {
    return vector(v.z * y - v.y * z, v.x * z - v.z * x, v.y * x - v.x * y);
  }

  //Normalization operator
  vector operator!() {
    return *this * (1 / sqrt(*this % *this));
  }
};

//Sphere positions:
int G[] = {133232, 133256, 69892, 127236, 69636, 40964, 40964, 16388, 0};

float randFloat() {
  return (float)rand() / RAND_MAX;
}

//Send a ray from the camera outward and see if we hit the sky, ground, or sphere
int trace(vector start, vector end, vector &normal, float &distance) {
  distance = 1e9;
  int hit = 0; //0 = upward ray (no hit), 1 = downward ray (no hit), 2 = ray hit

  //check if the ray actually points downward, not upward:
  float direction = -start.z / end.z;
  if(.01 < direction) {
    distance = direction;
    normal = vector(0, 0, 1);
    hit = 1;
  }

  for(int i = 19; i--;) //Hardcoded number of columns
    for(int j = 9; j--;) //Hardcoded array size of reflective spheres (size of G[])
      if(G[j] & 1 << i) {
        vector v = start + vector(-i, 0, -j - 4);
        float b = v % end; //Remember: that's dot product!
        float c = v % v - 1;
        float q = b * b - c;

        //Determine if the sphere was hit:
        if(q > 0) {
          float s = -b - sqrt(q);
          //If it hits the sphere, get the distance from the camera to sphere
          if(s < distance && s > .01) {
            distance = s;
            normal = !(v + end * distance); //Cross-product!
            hit = 2;
          }
        }
      }
  return hit;
}

vector sample(vector start, vector end) {
  float distance;
  vector normal;
  int match = trace(start, end, normal, distance);

  //If the ray went upward and hit nothing, draw a cloudless, blue sky:
  if(!match) {
    //Draw the sky:
    float gradient = pow(1 - end.z, 8);
    return vector(gradient * .53, gradient * .81, pow(1 - end.z, 2) * .92);
  }

  //Look for a hit:
  vector intersection = start + end * distance;
  vector lightDirection = !(vector(9 + randFloat(), 9 + randFloat(), 16) + intersection * -1);
  vector halfVector = end + normal * (normal % end * -2);

  //Lambert:
  float lambertFactor = lightDirection % normal;

  if(lambertFactor < 0 || trace(intersection, lightDirection, normal, distance)) {
    lambertFactor = 0;
  }

  float color = pow(lightDirection % halfVector * (lambertFactor > 0), 99);

  //If match is 1, nothing was hit and the ray goes downward: draw a floor color
  if(match & 1) {
      intersection = intersection * .2;
      return ((int)(ceil(intersection.x) + ceil(intersection.y)) & 1 ? vector(2, 2, 2) : vector(1, 1, 1)) * (lambertFactor * .2 + .1);
  }

  //Last case: match is 2, which is a hit.
  //Cast a new ray and return a color that gets half as colorful per bounce.
  return vector(color, color, color) + sample(intersection, halfVector) * .5;
}

int main() {
  vector camForward = !(vector(-3, -22, 3));
  vector camUp = !(vector(0, 0, 1) ^ camForward) * .002;
  vector camRight = !(camForward ^ camUp) * .002, c = (camUp + camRight) * -400 + camForward;

  //Print the .ppm header:
  printf("P6 512 512 255 ");
  //512x512px image as seen above and below
  for(int y = 512; y--;)
    for(int x = 512; x--;) {
      vector color(13, 13, 13);
      for(int nRays = 64; nRays--;) { //64 rays per pixel
        vector delta = camUp * (randFloat() - .5) * 99 + camRight * (randFloat() - .5) * 99;
        color = sample(vector(17, 16, 8) + delta, !(delta * -1 + (camUp * (randFloat() + x) + camRight * (y + randFloat()) + c) * 16)) * 3.5 + color;
      }
      //Print each pixel's data:
      printf("%c%c%c", (int)color.x, (int)color.y, (int)color.z);
    }
}