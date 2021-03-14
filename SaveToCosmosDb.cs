using IoTHubTrigger = Microsoft.Azure.WebJobs.EventHubTriggerAttribute;

using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;

namespace AzureFunctions
{
    public static class SaveToCosmosDb
    {


        [FunctionName("SaveToCosmosDb")]
        public static void Run(
            [IoTHubTrigger("messages/events", Connection = "IotHub", ConsumerGroup = "cosmosinlupp")] EventData message,
            [CosmosDB(
                databaseName:"IOT20INLUPPEN14",
                collectionName:"Measurements",
     
                ConnectionStringSetting = "CosmosDb",
                CreateIfNotExists = true
                
            )] out dynamic cosmosdb,
            ILogger log
        )
        {
            var msg = JsonConvert.DeserializeObject<DhtMeasurement> (Encoding.UTF8.GetString(message.Body.Array));
            msg.DeviceId = message.SystemProperties["iothub-connection-device-id"].ToString();
            msg.Name = message.Properties["name"].ToString();
            msg.SkolNamn = message.Properties["Skolnamn"].ToString();

            var json = JsonConvert.SerializeObject(msg);
            cosmosdb = json;

            //log.LogInformation($"C# IoT Hub trigger function processed a message: {Encoding.UTF8.GetString(message.Body.Array)}");
            //cosmosdb = Encoding.UTF8.GetString(message.Body.Array);
        }
    }
}