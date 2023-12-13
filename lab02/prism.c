#include <stdio.h>

int main()
{
	int length = 0, width = 0, height = 0;

	printf("Please enter prism length: ");
	scanf("%d", &length);
	
	printf("Please enter prism width: ");
	scanf("%d", &width);

	printf("Please enter prism height: ");
	scanf("%d", &height);

	int volume = length*width*height;
	int area = 2*length*width + 2*length*height + 2*width*height;
	int edgeLength = 4*width + 4*length + 4*height;

	printf("A prism with sides %d %d %d has:\nVolume      = %d\nArea        = %d\nEdge length = %d\n", length, width, height, volume, area, edgeLength);

	return 0;
}
