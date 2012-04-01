using System;
using System.Collections.Generic;
using System.Text;

namespace AFSKTable
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine ("const int32_t freqTable[256] =");
            System.Console.WriteLine ("{");

            for (int i = 0; i < 256; ++i)
            {
                System.Console.Write((2500.0 * Math.Sin(2 * Math.PI * (Double)i / 256.0)).ToString("f0"));

                if (i != 255)
                    System.Console.Write(", ");

                if (((i + 1) % 16) == 0)
                    System.Console.WriteLine();
            } // END for

            System.Console.WriteLine("};");

            System.Console.WriteLine();

            int lastValue = -1;
            int count = 0;

            for (int i = 0; count <= 100 && i < 4096; ++i)
            {
                double hum = -4.0 + (0.0405 * (double)i) - (2.8e-6 * (double)i * (double)i)+ .5;

                if ((int)(hum) > lastValue)
                {
                    lastValue = (int)hum;
                    System.Console.Write(i.ToString() + ", ");
                    ++count;

                    if (((count - 1) % 10) == 0)
                        System.Console.WriteLine();
                }
            } // END for

            System.Console.WriteLine();

        }
    }
}
