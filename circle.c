#include<Enguin/Enguin.h>

// Algorithm:
//         Begin {Circle}
//         x := r;
//         y := 0;
//         d := 1 - r;
//         Repeat
//         Circle_Points(x,y);
//         y := y + 1;
//         if d < 0 Then
//             d := d + 2*y + 1
//         Else Begin
//             x := x - 1;
//             d := d + 2*(y-x) + 1
//             End
//         Until x < y
//         End; {Circle}


int main()
{
	return 0;
}
