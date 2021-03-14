using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json.Serialization;

namespace AzureFunctions.Models
{
    //{"deviceId":"device1","temperature":11,"humidity":44}
    public class DeviceMessage
    {
        public string DeviceId { get; set; }
        public decimal Temperature { get; set; }
        public decimal Humidity { get; set; }
    }
}
