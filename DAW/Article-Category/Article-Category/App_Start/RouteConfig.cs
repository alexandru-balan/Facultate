using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Laborator4
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "CategoryIndex",
                url: "{controller}/{action}",
                defaults: new {controller = "Category", action = "Index"}
                );

            routes.MapRoute(
                name: "CategoryShow",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Category", action = "Show", id = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "CategoryEdit",
                url: "{controller}/{action}",
                defaults: new { controller = "Category", action = "Edit" }
                );

            routes.MapRoute(
                name: "CategoryEditPost",
                url: "{controller}/{action}/{id}/{category}",
                defaults: new { controller = "Category", action = "Edit" }
                );

            routes.MapRoute(
                name: "CategoryNew",
                url: "{controller}/{action}/",
                defaults: new { controller = "Category", action = "New" }
                );

            routes.MapRoute(
                name: "CategoryNewPost",
                url: "{controller}/{action}/{category}",
                defaults: new { controller = "Category", action = "New" }
                );

            routes.MapRoute(
               name: "CategoryDelete",
               url: "{controller}/{action}/{id}",
               defaults: new { controller = "Category", action = "Delete" }
               );

            routes.MapRoute(
               name: "ArticleNew",
               url: "{controller}/{action}",
               defaults: new { controller = "Article", action = "New" }
               );

            routes.MapRoute(
               name: "ArticleNewPost",
               url: "{controller}/{action}/{article}",
               defaults: new { controller = "Article", action = "New" }
               );

            routes.MapRoute(
               name: "ArticleIndex",
               url: "{controller}/{action}",
               defaults: new { controller = "Article", action = "Index" }
               );

            routes.MapRoute(
              name: "ArticleShow",
              url: "{controller}/{action}/{id}",
              defaults: new { controller = "Article", action = "Show" }
              );

            routes.MapRoute(
              name: "ArticleEdit",
              url: "{controller}/{action}/{id}",
              defaults: new { controller = "Article", action = "Edit" }
              );

            routes.MapRoute(
              name: "ArticleEditPut",
              url: "{controller}/{action}/{id}/{article}",
              defaults: new { controller = "Article", action = "Edit" }
              );

            routes.MapRoute(
              name: "ArticleDelete",
              url: "{controller}/{action}/{id}",
              defaults: new { controller = "Article", action = "Delete" }
              );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );
        }
    }
}
