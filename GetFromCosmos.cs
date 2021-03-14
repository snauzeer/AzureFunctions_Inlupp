using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;

namespace AzureFunctions
{
    public static class GetFromCosmos
    {
        [FunctionName("GetFromCosmos")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = null)] HttpRequest req,
            [CosmosDB(
                databaseName:"IOT20INLUPPEN14",
                collectionName:"Measurements",
                CreateIfNotExists = true,
                ConnectionStringSetting = "CosmosDb",
                
                SqlQuery = "SELECT TOP 10 * FROM c ORDER BY c.TimeStamp DESC")] IEnumerable<DhtMeasurement> cosmosdb,
            ILogger log)
        {
           
            return new OkObjectResult(cosmosdb);
        }
    }
}

