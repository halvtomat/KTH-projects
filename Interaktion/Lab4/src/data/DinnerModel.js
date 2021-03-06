import ObservableModel from "./ObservableModel";
import * as ApiConfig from "./apiConfig";

const BASE_URL = ApiConfig.ENDPOINT;
const httpOptions = {
  headers: { method: "GET", "X-Mashape-Key": ApiConfig.API_KEY }
};

class DinnerModel extends ObservableModel {
  constructor() {
    super();
    this._numberOfGuests = 0;
    this.menu = [];
    (localStorage.getItem("guests") !== null) ? this._numberOfGuests = localStorage.getItem("guests") : this._numberOfGuests = 0;
    try{
      this.menu = JSON.parse(localStorage.getItem("menu"));
    } catch(e){}
  }

  /**
   * Get the number of guests
   * @returns {number}
   */
  getNumberOfGuests() {
    return this._numberOfGuests;
  }

  /**
   * Set number of guests
   * @param {number} num
   */
  setNumberOfGuests(num) {
    this._numberOfGuests = num;
    this.notifyObservers();
    localStorage.setItem("guests",num);
  }

  // API methods

  /**
   * Do an API call to the search API endpoint.
   * @returns {Promise<any>}
   */
  getAllDishes(type, query) {
    if(type == null) type = "main course";
    if(query == null) query = "pizza";
    const url = `${BASE_URL}/recipes/search?type=${type}&query=${query}`;
    return fetch(url, httpOptions).then(this.processResponse);
  }

  getFullMenu() {
    return this.menu;
  }

  getAllIngredients() {
    return this.menu.map(function(dish){
      return dish.extendedIngredients;
    }).flat();
  }

  getTotalMenuPrice() {
    if(this.menu.length === 0) return 0;
    let temp = this.menu.reduce((dish1, dish2) => ({pricePerServing: dish1.pricePerServing + dish2.pricePerServing}));
    return temp.pricePerServing * this.getNumberOfGuests();
  }

  //Adds the passed dish to the menu.
  addDishToMenu(dish) {
    this.menu.push(dish);
    localStorage.setItem("menu", JSON.stringify(this.menu));
  }

  //Removes dish with specified id from menu
  removeDishFromMenu(id) {
    this.menu.splice(this.menu.indexOf(this.getDish(id)),1);
    this.notifyObservers();
    localStorage.setItem("menu", JSON.stringify(this.menu));
  }

  getDish(id) {
    const url = `${BASE_URL}/recipes/${id}/information`;
    return fetch(url, httpOptions).then(this.processResponse);
  }

  processResponse(response) {
    if (response.ok) {
      return response.json();
    }
    throw response;
  }
}

// Export an instance of DinnerModel
const modelInstance = new DinnerModel();
export default modelInstance;