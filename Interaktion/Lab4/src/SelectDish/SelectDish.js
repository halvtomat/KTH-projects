import React, { Component } from "react";
import Sidebar from "../Sidebar/Sidebar";
import Dishes from "../Dishes/Dishes";
import Details from "../Details/Details";
import Search from "../Search/Search";
import "./SelectDish.css";

class SelectDish extends Component {
  constructor(props) {
    super(props);
    this.state = {
      status: "Search"
    };
  }

  getDetails = (id) => {
    this.setState = ({
      status: "Details"
    });
    console.log(id);
  }
  searchDishes = (type, query) => {
    
  }

  render() {
    switch(this.state.status){
      case "Search":
        return (
          <div className="SelectDish">
            <Sidebar model={this.props.model} />
            <Search  searchDishes={this.searchDishes}/>
            <Dishes getDetails={this.getDetails}/>
          </div>
        );
      case "Details":
        return (
          <div className="SelectDish">
            <Sidebar model={this.props.model} />
            <Details  />
          </div>
        );
    }

  }
}

export default SelectDish;
