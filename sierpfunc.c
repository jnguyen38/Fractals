// Recursive function to generate the Sierpinski triangle fractal.
// From main, you would call this function to draw the outer triangle.
// The function will then recurse to draw all the inner triangles
// (you will of course have to write a triangle drawing function).
// NOTE:
// you may only use this code if you fully understand how it works.

void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
   // Base case. 
   if( abs(x2-x1) < 5 ) return;

   // Draw the triangle
   mytriangledrawingfunction( x1, y1, x2, y2, x3, y3 );

   // Recursive calls
   sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
   sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
   sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

