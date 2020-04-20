// Grundläggande saker som sätter upp lambda-funktionen
const AWS = require('aws-sdk');
const docClient = new AWS.DynamoDB.DocumentClient({
    region: 'us-east-1'
});
exports.handler = function index(e, ctx, callback) {

    if (!e.queryStringParameters.hasOwnProperty("name")) {
        callback(null, {
            statusCode: 400, // Bad Request
            headers: {
                'Content-Type': 'application/json',
                "Access-Control-Allow-Origin": "*" // Behövs för att CORS ska fungera
            },
            body: JSON.stringify({
                message: "No 'name' query string provided. Examine your IoT device for its unique name." //Skickas om ingen "name" parameter skickas
            })
        });
        return false;
    }
    
        if (e.body) {
        const body = JSON.parse(e.body); //Avaktivera Jsonparse om du testar i lambda


    console.log(e);
    var params = {

        TableName: "DriverBotLog",

        Key: { //Lägger in nyckelvärdena 

            "Bot": e.queryStringParameters.name

        },

        //Här nedan har vi UpdateExpression, där säger vi vilka attribut i objektet som ska länkas till vilka bokstäver. 
        UpdateExpression: "set   #s = list_append(#s, :y), #a = list_append(#a, :i), #u = list_append(#u, :o), #d = list_append(#d, :g), LastUpdate=:u, CurrentSpeed= :t,  CurrentAngle= :h,  CurrentDir= :k",
        ExpressionAttributeNames: {         //Dessa attribut är de som kommer att ändras. 
            "#s": "Speed",
            "#a": "Angle",
            "#u": "UpdatedAt",
            "#d": "Direction"
        },
        ExpressionAttributeValues: {         //Dessa värden är de som kommer att ändras/läggas till. 
            ":y": [body.speed], //[] runt värdet gör det till en lista, detta behövs då list_append tar bara emot listor och sammanfogar dem.
            ":i": [body.angle],
            ":g": [body.dir],
            ":o": [new Date().toUTCString()],
            ":t": body.speed,
            ":h": body.angle,
            ":k": body.dir,
            ":u": new Date().toUTCString()
        },
        ReturnValues: "UPDATED_NEW" //Man skickar ett returnvalue för att den ska veta att den ska uppdateras. 

    };

    console.log("Updating the item...");

    docClient.update(params, function (err, data) {
        if (err) {
            const response = {
                statusCode: 400,
                headers: {
                    'Content-Type': 'application/json',
                    "Access-Control-Allow-Origin": "*" // Behövs för att CORS ska fungera
                },
                body: JSON.stringify('Gick inte att uppdatera IoT-enheten, försök igen eller titta på datan du skickar!'), //Skickas om det blev en error
            };
            callback(err, response);
        } else {
            const response = {
                headers: {
                    'Content-Type': 'application/json',
                    "Access-Control-Allow-Origin": "*" // Behövs för att CORS ska fungera
                },
                statusCode: 200,
                body: JSON.stringify('Iot-enheten ' + e.queryStringParameters.name + ' är uppdaterad!'), //Skickas om allt gått bra
            };
            callback(null, response);
        }

    });
}
};