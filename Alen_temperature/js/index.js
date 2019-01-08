function loadXMLData() {
    var request = new XMLHttpRequest();
    var tempValue;
    var nizTemp = new Array();
    request.onreadystatechange = function () {
        if(request.readyState == 4 && request.status == 200){
            var response = request.responseText;
            var dataField = JSON.parse(response);
            var field = dataField["feeds"];
            field.forEach(function(entry){
                tempValue = entry["field1"];
                nizTemp.push(tempValue);
            });

            document.getElementById("temp--data-1").innerHTML = tempValue;
            document.getElementById("temp--data-2").innerHTML = tempValue;
            document.getElementById("temp--data-3").innerHTML = tempValue;
            document.getElementById("temp--data-4").innerHTML = tempValue;
        }
    };

    request.open("GET", "https://api.thingspeak.com/channels/659276/feeds.json?api_key=LHIW370MZYTTAS94&results=2", true);
    request.send();
}