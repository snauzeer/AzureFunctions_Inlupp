using System;
using System.Collections.Generic;
using System.Text;

namespace AzureFunctions
{
    public class DhtMeasurement
    {
        public string DeviceId { get; set; }

        public string Name { get; set; }

        public string SkolNamn { get; set; }
        //public string Skolnamn { get; internal set; }
        public float Temperature { get; set; }

        public float Humidity { get; set; }
        
        public float TimeStamp { get; set; }

    }
}
