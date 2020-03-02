import React, { Component } from "react";
import Sidebar from "../Sidebar/Sidebar";
import Dishes from "../Dishes/Dishes";
import "./SelectDish.css";

class SelectDish extends Component {
  render() {
    return (
      <div className="SelectDish">
        <div className="SearchDish">
          <h2 id="topText">This is the Select Dish screen</h2>
          <input type="text" id="keyWords" placeholder="Enter key words"></input>
          <button type="submit" id="submit" className="button">search</button>
          <select id="select">
            <option value="All">All</option>
            <option value="Main Course">Main Course</option>
            <option value="Side Dish">Side Dish</option>
            <option value="Dessert">Dessert</option>
            <option value="Appetizer">Appetizer</option>
          </select>
        </div>
        {/* We pass the model as property to the Sidebar component */}
        <Sidebar model={this.props.model} />
        <Dishes />
      </div>
    );
  }
}

export default SelectDish;
