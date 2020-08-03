//DinnerModel class
class DinnerModel {

  constructor() {
    this.guests = 0;
    this.menu = new Array();
    this.observer = [];
  }
  
  addObserver(o){
    this.observer.push(o);
  }

  notifyObserver(){
    for(var i = 0; i < this.observer.length; i++){
      this.observer[i].update(this);
    }
    localStorage.setItem('guests', this.getNumberOfGuests());
  }

  setNumberOfGuests(num) {
    if(num < 1) this.guests = 1;
    else this.guests = num;
  }

  getNumberOfGuests() {
    return this.guests;
  }

  //Returns the dishes that are on the menu for selected type
  getSelectedDishes(type) {
    return this.menu.filter(function(dish){
      if( dish.type == type) return dish;
    });
  }

  //Returns all the dishes on the menu.
  getFullMenu() {
    return this.menu;
  }

  //Returns all ingredients for all the dishes on the menu.
  getAllIngredients() {
    return this.menu.map(function(dish){
      return dish.extendedIngredients;
    }).flat();
  }

  //Returns the total price of the menu (price per serving of each dish multiplied by number of guests).
  getTotalMenuPrice() {
    let temp = this.menu.reduce((dish1, dish2) => ({pricePerServing: dish1.pricePerServing + dish2.pricePerServing}));
    return temp.pricePerServing * this.getNumberOfGuests();
  }

  //Adds the passed dish to the menu.
  addDishToMenu(dish) {
    this.menu.push(dish);
  }

  //Removes dish with specified id from menu
  removeDishFromMenu(id) {
    this.menu.splice(this.menu.indexOf(this.getDish(id)),1);
  }

  //Returns all dishes of specific type (i.e. "starter", "main dish" or "dessert").
  //query argument, text, if passed only returns dishes that contain the query in name or one of the ingredients.
  //if you don't pass any query, all the dishes will be returned
  getAllDishes(type, query) {
    displayLoader();
    if(type == null) type = "main course";
    if(query == null) query = "pizza";

    return fetch(ENDPOINT+"/recipes/search?type="+ type +"&query="+ query,
      {
        headers:{
          method: "GET",
          "X-Mashape-Key" :  API_KEY
        }
      })
    .then((response) => {
      if(response.status !== 200) throw new Error("Not 200");
      else return response;
    })
    .then(response => response.json())
    .then(data => data.results)
    .catch(console.log)
    .finally(nothing => {
      hideLoader();
    });
  }

  //Returns a dish of specific ID
  getDish(id) {
    displayLoader();
    return fetch( ENDPOINT+"/recipes/"+ id + "/information",
      {
        headers: {
          method:  "GET",
          "X-Mashape-Key": API_KEY
        }
      })
    .then((response) => {
      if(response.status !== 200) throw new Error("Not 200");
      else return response;
    })
    .then(response => response.json())
    .then(data => data)
    .catch(console.log)
    .finally(nothing => {
      hideLoader();
    });
  }
}
function displayLoader(){
  document.querySelector("#loader").style.display = "block";
}
function hideLoader(){
  document.querySelector("#loader").style.display = "none";
}