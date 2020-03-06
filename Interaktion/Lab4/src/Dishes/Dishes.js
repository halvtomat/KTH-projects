import React, { Component } from "react";
// Alternative to passing the moderl as the component property,
// we can import the model instance directly
import modelInstance from "../data/DinnerModel";
import "./Dishes.css";
import Link from "react-router-dom/Link";

class Dishes extends Component {
  constructor(props) {
    super(props);
    // We create the state to store the various statuses
    // e.g. API data loading or error
    this.state = {
      status: "LOADING"
    };
    this.keyword = "pizza";
    this.query = "All";
  }

  // this methods is called by React lifecycle when the
  // component is actually shown to the user (mounted to DOM)
  // that's a good place to call the API and get the data
  componentDidMount() {
    this.getDishes();
  }

  setKeyword = (evt) => {
    this.keyword = evt.target.value;
  }

  setQuery = (evt) => {
    this.query = evt.target.value;
  }

  getDishes() {
    this.setState({
      status: "LOADING"
    })
    // when data is retrieved we update the state
    // this will cause the component to re-render
    modelInstance
      .getAllDishes(this.keyword, this.query)
      .then(dishes => {
        this.setState({
          status: "LOADED",
          dishes: dishes.results
        });
      })
      .catch(() => {
        this.setState({
          status: "ERROR"
        });
      });
  }

  render() {
    let dishesList = null;
    // depending on the state we either generate
    // useful message to the user or show the list
    // of returned dishes
    switch (this.state.status) {
      case "LOADING":
        dishesList = <em>Loading...</em>;
        break;
      case "LOADED":
        dishesList = this.state.dishes.map(dish => (
          <Link key={dish.id}  to={"/dish/"+dish.id}>
            <img 
              className="image" 
              alt={dish.name}
              src={"https://spoonacular.com/recipeImages/"+dish.id+"-556x370.jpg"}> 
              {dish.name}
            </img>
          </Link>
        ));
        break;
      default:
        dishesList = <b>BIG ERROR</b>;
        break;
    }

    return (
      <div className="Dishes">
        <div className="Search">
          <h2 id="topText">This is the Search screen</h2>
          <input type="text" id="keyWords" placeholder="Enter key words" onChange={evt => this.setKeyword(evt)}></input>
          <button type="submit" className="button" id="submit" onClick={() => this.getDishes()}>search</button>
          <select id="select" onChange={evt => this.setQuery(evt)}>
            <option value="All">All</option>
            <option value="Main Course">Main Course</option>
            <option value="Side Dish">Side Dish</option>
            <option value="Dessert">Dessert</option>
            <option value="Appetizer">Appetizer</option>
          </select>
        </div>
        <div className="DishesList">
          <ul>{dishesList}</ul>
        </div>
      </div>
    );
  }
}

export default Dishes;
