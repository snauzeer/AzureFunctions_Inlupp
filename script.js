

let tabledata = document.getElementById('tabledata')

fetch('https://iot20-fa.azurewebsites.net/api/GetFromCosmos?')
.then(res => res.json())
.then(data => {
    console.log(data)
    for(let row of data) {
        const dateObject = new Date(row.Logged * 1000)
        
        
        tabledata.innerHTML += `<tr>
                                        
                                      <td>${row.deviceId}</td>
                                      <td>${toIso(row.timeStamp)}</td>
                                      <td>${row.temperature.toFixed(2)}</td>
                                      <td>${row.humidity.toFixed(2)}</td>`
        
    }
})

function toIso(timestamp)
{
    var datetime = new Date(timestamp * 1000);
    return datetime.toUTCString();
}