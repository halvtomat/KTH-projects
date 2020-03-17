import * as ApiConfig from "./apiConfig";

const BASE_URL = ApiConfig.ENDPOINT;
const KEY = ApiConfig.API_KEY;
const httpOptions = {
    headers: { method: "GET"}
};

class WeatherModel{
    constructor(){
    }

    getCurrentWeather(){
        const url = `${BASE_URL}q=Stockholm,sweden&appid=${KEY}`;
        return fetch(url, httpOptions).then(this.processResponse);
    }

    processResponse(response){
        if(response.ok){
            return response.json();
        }
        throw response;
    }
}

// Export an instance of WeatherModel
const modelInstance = new WeatherModel();
export default modelInstance;