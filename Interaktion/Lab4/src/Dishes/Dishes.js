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
      status: "LOADING",
      type: this.props.type,
      query: this.props.query
    };
  }
  static getDerivedStateFromProps(props, state){
    console.log("get derived state");
    return {
      type: props.type,
      query: props.query
    };
  }

  // this methods is called by React lifecycle when the
  // component is actually shown to the user (mounted to DOM)
  // that's a good place to call the API and get the data
  componentDidMount() {
    // when data is retrieved we update the state
    // this will cause the component to re-render
    modelInstance
      .getAllDishes(this.state.type, this.state.query)
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
//
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
          <Link key={dish.id}  to={"/dish/id"+dish.id} >
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
        <ul>{dishesList}</ul>
      </div>
    );
  }
}

export default Dishes;
