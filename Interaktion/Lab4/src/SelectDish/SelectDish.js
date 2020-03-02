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
      status: this.props.state,
      dishId: 0,
      type: "pizza",
      query: "All"
    };
  }
  
  searchDishes = (type, query) => {
    console.log(type);
    console.log(query);
    this.setState({
      status: "SEARCH",
      type: type,
      query: query
    },() => console.log("confirmed state change"))
  }

  render() {
    switch(this.state.status){
      case "SEARCH":
        return (
          <div className="SelectDish">
            <Sidebar model={this.props.model} />
            <Search searchDishes={this.searchDishes}/>
            <Dishes getDetails={this.getDetails} type={this.state.type} query={this.state.query}/>
          </div>
        );
      case "DETAILS":
        return (
          <div className="SelectDish">
            <Sidebar model={this.props.model} />
            <Details dishID={this.state.dishId}/>
          </div>
        );
      default:
        return ( 
        <div className="SelectDish">
          <h1>Something is horribly wrong</h1>
        </div>);
    }

  }
}

export default SelectDish;
