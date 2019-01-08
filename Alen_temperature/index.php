<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">

    <title>Server soba temperature</title>
    <link rel="stylesheet" href="css/index.css">
    <script type="text/javascript" src="js/index.js"></script>
</head>
<body onload="loadXMLData()">
    <div class="wrapper">
        <div class="table-wrapper">
            <div class="header">
                <h2 class="header--title">Server sobe</h2>
            </div>
            <div class="table">
                <div class="rows">
                    <div class="cells">
                        <h2>Sprat I - Soba 1</h2>
                        <label class="temp-label">Temperatura: </label>
                        <p class="data" id="temp--data-1"></p>
                        <label class="stagod">°C</label>
                    </div>
                    <div class="cells" id="cell2">
                        <h2>Sprat I - Soba 2</h2>
                        <label class="temp-label">Temperatura: </label>
                        <p class="data" id="temp--data-2"></p>
                        <label class="stagod">°C</label>
                    </div>
                </div>
                <div class="rows" id="row2">
                    <div class="cells">
                        <h2>Sprat II - Soba 1</h2>
                        <label class="temp-label">Temperatura: </label>
                        <p class="data" id="temp--data-3"></p>
                        <label class="stagod">°C</label>
                    </div>
                    <div class="cells" id="cell2">
                        <h2>Sprat II - Soba 2</h2>
                        <label class="temp-label">Temperatura: </label>
                        <p class="data" id="temp--data-4"></p>
                        <label class="stagod">°C</label>
                    </div>
                </div>
            </div>
        </div>
    </div>
</body>
</html>