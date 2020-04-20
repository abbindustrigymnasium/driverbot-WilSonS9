// Some basic things used to setup the lambda function
const AWS = require('aws-sdk');
const docCLient = new AWS.DynamoDB.DocumentClient({region: 'us-east-1'});
exports.handler = function index(e, ctx, callback) {
    
       if(!e.queryStringParameters.hasOwnProperty("Bot")) {
        callback(null, {
            statusCode: 400, // Bad Request
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                message: "No 'Bot' query string provided." //Detta skickas om ingen "Bot" parameter skickas
            })
        });
        return false;
    }
    var params = {
        // Här definieras vilken databas vi ska lägga till i samt vad som ska läggas in som ett nytt item
        Item: { Bot: e.queryStringParameters.Bot, Log: [{}]},
        TableName: 'DriverBotLog'
    };
    docCLient.put(params, function(err, data) {
        if (err) {
                let response = {
        statusCode: 400,
        body: JSON.stringify('Gick inte att lägga till boten, försök igen eller titta på datan du skickar!'), //Skickas om det blir en error
    };
            callback(err, response);
        } else {
              let response = {
        statusCode: 200,
        body: JSON.stringify('Ny bot tillagd! Med namnet '+e.queryStringParameters.Bot), //Skickas om allt gått bra
    };
            callback(null, response);
        }
    });
};