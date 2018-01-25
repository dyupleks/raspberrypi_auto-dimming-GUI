#include <stdio.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#define SPI_CHANNEL 0
#define SPI_SPEED 2000000
#define MCP_RESOLUTION 4096
#define MCP_REFVOL 5
#define MCP_CH_NUM 8
#define SPI_BUF_SIZE 3
#define MCP_SPI_SB 2
#define MCP_SPI_SD 1
#define MCP_SPI_D 20
#define MCP_SPI_D0 6
int readAnalog()
{
unsigned char spiBuf[SPI_BUF_SIZE];
int adcVal = 0;

spiBuf[0] = 0x6;
spiBuf[1] = 0b00000000;
spiBuf[2] = 0x00;
wiringPiSPIDataRW(SPI_CHANNEL, spiBuf, SPI_BUF_SIZE);
spiBuf[1] = 0x0F & spiBuf[1];
adcVal = (spiBuf[1] << 8) | spiBuf[2];
return adcVal;
}
int main()
{
int adcCh, adcVal = 0;
double convertVol = 0;
if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
	{
	printf("Error wiringPiSPISetup!\n");
	}
else
{
	printf("No errors: I'm okey!\n");
	while (1)
	{
	adcVal = readAnalog();
	convertVol = (double)adcVal / MCP_RESOLUTION * MCP_REFVOL;
	printf("ch%d: Digital val=%5d, %.2f(V)\n", adcCh, adcVal, convertVol);
	sleep(1);
	
	}
}
}
